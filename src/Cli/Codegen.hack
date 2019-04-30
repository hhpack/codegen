/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Cli;

use HHPack\Codegen\{ProjectFileGenerator, GeneratorName, ClassName};
use HHPack\Codegen\Contract\{Output, GeneratorProvider};
use HHPack\Codegen\Project\{PackageClassGenerator};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use function HHPack\Getopt\{optparser, take_on, on};
use HHPack\Getopt\Parser\{OptionParser};
use HHPack\Codegen\Cli\{CodegenGenerators};
use Facebook\DefinitionFinder\{TreeParser};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFile,
  CodegenFileResult,
};
use HH\Lib\{Vec, Str, Math};

final class Codegen {
  const string PROGRAM_NAME = 'codegen';
  const string PROGRAM_VERSION = '0.2.0';

  private bool $help = false;
  private bool $version = false;
  private OptionParser $optionParser;
  private GeneratorProvider $provider;

  public function __construct(private Output $output = new ConsoleOutput()) {
    $this->optionParser = optparser(
      [
        on(
          ['-h', '--help'],
          'Display help message',
          () ==> {
            $this->help = true;
          },
        ),
        on(
          ['-v', '--version'],
          'Display version',
          () ==> {
            $this->version = true;
          },
        ),
      ],
    );

    $config = HHAutoloadConfig::fromWorkingDirectory();
    $this->provider = new DevGeneratorProvider($config->devRoots());
  }

  public function run(Traversable<string> $argv): void {
    $args = ImmVector::fromItems($argv)->skip(1);

    $remainArgs = $this->optionParser->parse($args);

    if ($this->help) {
      $this->displayHelp();
    } else if ($this->version) {
      $this->displayVersion();
    } else {
      $type = $remainArgs->at(0);
      $name = $remainArgs->at(1);

      $this->generateBy(Pair {$type, $name});
    }
  }

  private function generateBy(
    Pair<GeneratorName, ClassName> $generateClass,
  ): void {
    $classFile = $this->generateFile($generateClass);
    $result = $classFile->save();

    if ($result === CodegenFileResult::CREATE) {
      $this->output
        ->info(\sprintf("File %s is created\n", $classFile->getFileName()));
    } else if ($result === CodegenFileResult::UPDATE) {
      $this->output
        ->info(\sprintf("File %s is updated\n", $classFile->getFileName()));
    } else if ($result === CodegenFileResult::NONE) {
      $this->output
        ->info(
          \sprintf("File %s is already exists\n", $classFile->getFileName()),
        );
    }
  }

  private function generateFile(
    Pair<GeneratorName, ClassName> $generateClass,
  ): CodegenFile {
    $generators = $this->provider->generators();

    $generator = ProjectFileGenerator::fromItems($generators);
    return $generator->generate($generateClass);
  }

  private function displayVersion(): void {
    $this->output
      ->info(
        \sprintf("%s - %s\n", static::PROGRAM_NAME, static::PROGRAM_VERSION),
      );
  }

  private function displayHelp(): void {
    $this->output
      ->info(
        \sprintf("Usage: %s [OPTIONS] [GEN] [NAME]\n\n", static::PROGRAM_NAME),
      );
    $this->output
      ->info(\sprintf(
        "Arguments:\n%s\n  NAME: generate class name (ex. Foo\\Bar)\n\n",
        $this->generatorHelp(),
      ));
    $this->optionParser->displayHelp();
  }

  private function generatorHelp(): string {
    $mappedGenerators = $this->provider->generators();

    $generators = ImmVector::fromItems($mappedGenerators);

    $nameLength = Vec\map(
      $generators,
      ($generator) ==> {
        return Str\length($generator->name());
      },
    )
      |> Math\max($$);

    $formatter = ($generator) ==> {
      $paddingName = $generator->name();
      if ($nameLength !== null) {
        $paddingName = Str\pad_right($generator->name(), $nameLength);
      }
      return \sprintf("    %s   %s", $paddingName, $generator->description());
    };

    $help = Vec\map($generators, $formatter)
      |> Str\join($$, "\n");

    return \sprintf("   GEN: generator name (ex. lib, test)\n%s\n", $help);
  }
}

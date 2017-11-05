<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Cli;

use HHPack\Codegen\{
  LibraryFileGenerator,
  ClassFileGenerator,
  GenerateType,
  ClassFileGeneratable,
  OutputNamespace
};
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
  CodegenFileResult
};

final class Codegen {
  const string PROGRAM_NAME = 'codegen';
  const string PROGRAM_VERSION = '0.1.1';

  private bool $help = false;
  private bool $version = false;
  private OptionParser $optionParser;
  private GeneratorProvider $provider;

  public function __construct() {
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

    $this->provider = new DevGeneratorProvider(dev_roots());
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
      //      $genType = GenerateType::assert($type);

      $this->generateBy(Pair {$type, $name});
    }
  }

  private function generateBy(
    Pair<GenerateType, string> $generateClass,
  ): void {
    $classFile = $this->generateFile($generateClass);
    $result = $classFile->save();

    if ($result === CodegenFileResult::CREATE) {
      fwrite(
        STDOUT,
        sprintf("File %s is created\n", $classFile->getFileName()),
      );
    } else if ($result === CodegenFileResult::UPDATE) {
      fwrite(
        STDOUT,
        sprintf("File %s is updated\n", $classFile->getFileName()),
      );
    } else if ($result === CodegenFileResult::NONE) {
      fwrite(
        STDOUT,
        sprintf("File %s is already exists\n", $classFile->getFileName()),
      );
    }
  }

  private function generateFile(
    Pair<GenerateType, string> $generateClass,
  ): CodegenFile {
    $generators = $this->provider->generators();

    $generator = LibraryFileGenerator::fromItems($generators);
    return $generator->generate($generateClass);
  }

  private function displayVersion(): void {
    fwrite(
      STDOUT,
      sprintf("%s - %s\n", static::PROGRAM_NAME, static::PROGRAM_VERSION),
    );
  }

  private function displayHelp(): void {
    fwrite(
      STDOUT,
      sprintf("Usage: %s [OPTIONS] [TYPE] [NAME]\n\n", static::PROGRAM_NAME),
    );
    fwrite(STDOUT, "Arguments:\n");
    fwrite(STDOUT, "  TYPE: generate type (ex. lib, test) \n");
    fwrite(STDOUT, "  NAME: generate class name (ex. Foo\\Bar)\n\n");
    $this->optionParser->displayHelp();
  }

}

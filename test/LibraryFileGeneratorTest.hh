<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\{
  LibraryFileGenerator,
  GenerateType,
  ClassFileGenerator,
  OutputNamespace
};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use Facebook\HackCodegen\{HackCodegenFactory, HackCodegenConfig};
use HackPack\HackUnit\Contract\Assert;

final class LibraryFileGeneratorTest {
  const string GENERATE_CLASS_NAME = 'Test\\Test1';

  public function __construct(private LibraryFileGenerator $generator) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $namespace = new OutputNamespace('Foo\\Bar', getcwd().'/tmp');
    $libraryGenerator = LibraryFileGenerator::fromItems(
      [
        Pair {
          GenerateType::TestClass,
          Pair {$namespace, TestClassGenerator::class},
        },
      ],
    );

    return new self($libraryGenerator);
  }

  <<Setup('Factory')>>
  public function removeClassFile(): void {
    $file = getcwd().'/tmp/Test/Test1.hh';

    if (!file_exists($file)) {
      return;
    }
    unlink($file);
  }

  <<Test('Factory')>>
  public function test(Assert $assert): void {
    $newTestClass = Pair {
      GenerateType::TestClass,
      static::GENERATE_CLASS_NAME,
    };
    $this->generator->generate($newTestClass)->save();

    $assert->bool(file_exists(getcwd().'/tmp/Test/Test1.hh'))->is(true);
  }

}

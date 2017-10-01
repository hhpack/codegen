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

  public function __construct(
    private LibraryFileGenerator $generator,
    private string $tempDirectory,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $tempDirectory = sys_get_temp_dir();
    $namespace = new OutputNamespace('Foo\\Bar', $tempDirectory);
    $libraryGenerator = LibraryFileGenerator::fromItems(
      [
        Pair {
          GenerateType::TestClass,
          $namespace->map(TestClassGenerator::class),
        },
      ],
    );

    return new self($libraryGenerator, $tempDirectory);
  }

  <<Setup('Factory')>>
  public function removeClassFile(): void {
    $file = sprintf("%s/%s", $this->tempDirectory, 'Test/Test1.hh');

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

    $file = sprintf("%s/%s", $this->tempDirectory, 'Test/Test1.hh');
    $assert->bool(file_exists($file))->is(true);
  }

}

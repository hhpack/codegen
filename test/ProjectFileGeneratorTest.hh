<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\{ProjectFileGenerator, OutputNamespace};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFileResult
};
use HackPack\HackUnit\Contract\Assert;
use HHPack\Codegen\Test\Mock\{NamedGeneratorMock};

final class ProjectFileGeneratorTest {
  const string GENERATE_CLASS_NAME = 'Test\\Test1';

  public function __construct(
    private ProjectFileGenerator $generator,
    private string $tempDirectory,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $tempDirectory = \sys_get_temp_dir();
    $namespace = new OutputNamespace('Foo\\Bar', $tempDirectory);
    $projectGenerator = ProjectFileGenerator::fromItems(
      [
        new NamedGeneratorMock(
          "test",
          "test",
          $namespace->map(TestClassGenerator::class),
        ),
      ],
    );
    return new self($projectGenerator, $tempDirectory);
  }

  <<Setup('test')>>
  public function removeClassFile(): void {
    $file = \sprintf("%s/%s", $this->tempDirectory, 'Test/Test1.hh');

    if (!\file_exists($file)) {
      return;
    }
    \unlink($file);
  }

  <<Test('Factory')>>
  public function test(Assert $assert): void {
    $newTestClass = Pair {'test', static::GENERATE_CLASS_NAME};
    $result = $this->generator->generate($newTestClass)->save();

    $file = \sprintf("%s/%s", $this->tempDirectory, 'Test/Test1.hh');
    $assert->bool($result === CodegenFileResult::CREATE)->is(true);
    $assert->bool(\file_exists($file))->is(true);
  }

}

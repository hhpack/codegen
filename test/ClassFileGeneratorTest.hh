<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\{ClassFileGenerator, OutputNamespace};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFileResult
};
use HackPack\HackUnit\Contract\Assert;

final class ClassFileGeneratorTest {

  const string GENERATE_CLASS_NAME = 'Test\\Test1';

  public function __construct(
    private ClassFileGenerator $generator,
    private OutputNamespace $namespace,
    private string $tempDirectory,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $tempDirectory = sys_get_temp_dir();
    $namespace = new OutputNamespace('Foo\\Bar', $tempDirectory);
    $config = new HackCodegenConfig($namespace->path());
    $generator = new TestClassGenerator(new HackCodegenFactory($config));

    return new self(
      new ClassFileGenerator($namespace, $generator),
      $namespace,
      $tempDirectory,
    );
  }

  <<Setup('test')>>
  public function removeClassFile(): void {
    $file = sprintf("%s/%s", $this->tempDirectory, 'Test/Test1.hh');
    if (!file_exists($file)) {
      return;
    }
    unlink($file);
  }

  <<Test('Factory')>>
  public function test(Assert $assert): void {
    $file = sprintf("%s/%s", $this->tempDirectory, 'Test/Test1.hh');

    $result = $this->generator->generate(static::GENERATE_CLASS_NAME)->save();

    $assert->bool($result === CodegenFileResult::CREATE)->is(true);
    $assert->bool(file_exists($file))->is(true);
  }

}

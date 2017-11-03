<?hh //strict

namespace HHPack\Codegen\Test\HackUnit;

use HHPack\Codegen\{GenerateClass, OutputClassName};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use Facebook\HackCodegen\{HackCodegenFactory, HackCodegenConfig, CodegenFileResult};
use HackPack\HackUnit\Contract\Assert;

final class TestClassGeneratorTest {

  const string NS = 'Foo\\Bar\\Test';
  const string CN = 'Test1';
  const string CF = 'Test/Test1.hh';

  public function __construct(
    private TestClassGenerator $generator,
    private HackCodegenConfig $config,
    private string $tempDirectory,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $tempDirectory = sys_get_temp_dir();
    $config = new HackCodegenConfig($tempDirectory);
    $generator = new TestClassGenerator(new HackCodegenFactory($config));
    return new self($generator, $config, $tempDirectory);
  }

  <<Setup('test')>>
  public function removeClassFile(): void {
    $file = sprintf("%s/%s", $this->tempDirectory, static::CF);

    if (!file_exists($file)) {
      return;
    }
    unlink($file);
  }

  <<Test('Factory')>>
  public function test(Assert $assert): void {
    $className = new OutputClassName(static::NS, static::CN);
    $class = new GenerateClass($className, static::CF);

    $result = $this->generator->generate($class)->save();

    $file = sprintf("%s/%s", $this->tempDirectory, static::CF);

    $assert->bool($result === CodegenFileResult::CREATE)->is(true);
    $assert->bool(file_exists($file))->is(true);
  }

}

<?hh //strict

namespace HHPack\Codegen\Test\HackUnit;

use HHPack\Codegen\{GenerateClass, OutputClassName};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use Facebook\HackCodegen\{HackCodegenFactory, HackCodegenConfig};
use HackPack\HackUnit\Contract\Assert;

final class TestClassGeneratorTest {

  const string NS = 'Foo\\Bar\\Test';
  const string CN = 'Test1';
  const string CF = 'Test/Test1.hh';

  public function __construct(
    private TestClassGenerator $generator,
    private HackCodegenConfig $config,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $config = new HackCodegenConfig(getcwd().'/tmp');
    $generator = new TestClassGenerator(new HackCodegenFactory($config));
    return new self($generator, $config);
  }

  <<Setup('Factory')>>
  public function removeClassFile(): void {
    $file = getcwd().'/tmp/'.static::CF;

    if (!file_exists($file)) {
      return;
    }
    unlink($file);
  }

  <<Test('Factory')>>
  public function test(Assert $assert): void {
    $className = new OutputClassName(static::NS, static::CN);
    $class = new GenerateClass($className, static::CF);

    $this->generator->generate($class)->save();

    $assert->bool(file_exists(getcwd().'/tmp/'.static::CF))->is(true);
  }

}

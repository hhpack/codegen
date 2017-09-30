<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\{ClassFileGenerator, OutputNamespace};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use Facebook\HackCodegen\{HackCodegenFactory, HackCodegenConfig};
use HackPack\HackUnit\Contract\Assert;

final class ClassFileGeneratorTest {

  const string GENERATE_CLASS_NAME = 'Test\\Test1';

  public function __construct(
    private ClassFileGenerator $generator,
    private OutputNamespace $namespace,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $namespace = new OutputNamespace('Foo\\Bar', getcwd().'/tmp');
    $config = new HackCodegenConfig($namespace->path());
    $generator = new TestClassGenerator(new HackCodegenFactory($config));

    return
      new self(new ClassFileGenerator($namespace, $generator), $namespace);
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
    $this->generator->generate(static::GENERATE_CLASS_NAME)->save();

    $assert->bool(file_exists(getcwd().'/tmp/Test/Test1.hh'))->is(true);
  }

}

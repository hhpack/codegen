<?hh //strict

namespace HHPack\Codegen\Test\HackUnit;

use HHPack\Codegen\{GenerateClass, OutputClassName};
use HHPack\Codegen\Project\{PackageClassGenerator};
use Facebook\HackCodegen\{HackCodegenFactory, HackCodegenConfig};
use HackPack\HackUnit\Contract\Assert;

final class PackageClassGeneratorTest {

  const string NS = 'Foo\\Bar\\Library';
  const string CN = 'Library1';
  const string CF = 'Library/Library1.hh';

  public function __construct(
    private PackageClassGenerator $generator,
    private HackCodegenConfig $config,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $config = new HackCodegenConfig(getcwd().'/tmp');
    $generator = new PackageClassGenerator(new HackCodegenFactory($config));
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

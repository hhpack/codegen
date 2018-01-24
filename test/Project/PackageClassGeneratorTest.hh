<?hh //strict

namespace HHPack\Codegen\Test\HackUnit;

use HHPack\Codegen\{GenerateClass, OutputClassName};
use HHPack\Codegen\Project\{PackageClassGenerator};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFileResult
};
use HackPack\HackUnit\Contract\Assert;

final class PackageClassGeneratorTest {

  const string NS = 'Foo\\Bar\\Library';
  const string CN = 'Library1';
  const string CF = 'Library/Library1.hh';

  public function __construct(
    private PackageClassGenerator $generator,
    private HackCodegenConfig $config,
    private string $tempDirectory,
  ) {}

  <<SuiteProvider('Factory')>>
  public static function generatorFactory(): this {
    $tempDirectory = sys_get_temp_dir();
    $config = (new HackCodegenConfig())->withRootDir($tempDirectory);
    $generator = new PackageClassGenerator(new HackCodegenFactory($config));
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

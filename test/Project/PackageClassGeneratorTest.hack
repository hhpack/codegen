namespace HHPack\Codegen\Test\HackUnit;

use HHPack\Codegen\{GenerateClassFile, OutputClassName};
use HHPack\Codegen\Project\{PackageClassGenerator};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFileResult,
};
use type Facebook\HackTest\{HackTest, DataProvider};
use function Facebook\FBExpect\expect;

final class PackageClassGeneratorTest extends HackTest {

  const string NS = 'Foo\\Bar\\Library';
  const string CN = 'Library1';
  const string CF = 'Library/Library1.hack';

  <<__Memoize>>
  public function currentTempDirectory(): string {
    return \sys_get_temp_dir();
  }

  public function provideGenerator(): vec<(PackageClassGenerator)> {
    $config = (new HackCodegenConfig())->withRootDir(
      $this->currentTempDirectory(),
    );
    $generator = new PackageClassGenerator(new HackCodegenFactory($config));
    return vec[tuple($generator)];
  }

  public async function beforeEachTestAsync(): Awaitable<void> {
    $file = \sprintf("%s/%s", $this->currentTempDirectory(), static::CF);

    if (!\file_exists($file)) {
      return;
    }
    \unlink($file);
  }

  <<DataProvider('provideGenerator')>>
  public function test(PackageClassGenerator $generator): void {
    $className = new OutputClassName(static::NS, static::CN);
    $class = new GenerateClassFile($className, static::CF);

    $result = $generator->generate($class)->save();

    $file = \sprintf("%s/%s", $this->currentTempDirectory(), static::CF);

    expect($result === CodegenFileResult::CREATE)->toBeTrue();
    expect(\file_exists($file))->toBeTrue();
  }

}

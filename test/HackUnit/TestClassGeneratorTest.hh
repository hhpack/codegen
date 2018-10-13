<?hh //strict

namespace HHPack\Codegen\Test\HackUnit;

use HHPack\Codegen\{GenerateClassFile, OutputClassName};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFileResult,
};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class TestClassGeneratorTest extends HackTest {

  const string NS = 'Foo\\Bar\\Test';
  const string CN = 'Test1';
  const string CF = 'Test/Test1.hh';

  <<__Memoize>>
  public function currentTempDirectory(): string {
    return \sys_get_temp_dir();
  }

  public function provideGenerators(): vec<(TestClassGenerator)> {
    $config =
      (new HackCodegenConfig())->withRootDir($this->currentTempDirectory());
    $generator = new TestClassGenerator(new HackCodegenFactory($config));
    return vec[tuple($generator)];
  }

  public async function beforeEachTestAsync(): Awaitable<void> {
    $file = \sprintf("%s/%s", $this->currentTempDirectory(), static::CF);

    if (!\file_exists($file)) {
      return;
    }
    \unlink($file);
  }

  <<DataProvider('provideGenerators')>>
  public function testGenerateClassFile(TestClassGenerator $generator): void {
    $className = new OutputClassName(static::NS, static::CN);
    $class = new GenerateClassFile($className, static::CF);

    $result = $generator->generate($class)->save();
    $file = \sprintf("%s/%s", $this->currentTempDirectory(), static::CF);

    expect($result === CodegenFileResult::CREATE)->toBeTrue();
    expect(\file_exists($file))->toBeTrue();
  }

}

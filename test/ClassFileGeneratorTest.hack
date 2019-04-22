namespace HHPack\Codegen\Test;

use HHPack\Codegen\{ClassFileGenerator, OutputNamespace};
use HHPack\Codegen\HackTest\{TestClassGenerator};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFileResult,
};
use type Facebook\HackTest\{HackTest, DataProvider};
use function Facebook\FBExpect\expect;

final class ClassFileGeneratorTest extends HackTest {

  const string GENERATE_CLASS_NAME = 'Test\\Test1';

  public function provideGenerater(): vec<(ClassFileGenerator)> {
    $namespace = new OutputNamespace('Foo\\Bar', $this->currentTempDirectory());

    $config = (new HackCodegenConfig())->withRootDir($namespace->path());
    $generator = new TestClassGenerator(new HackCodegenFactory($config));

    return vec[tuple(new ClassFileGenerator($namespace, $generator))];
  }

  <<__Memoize>>
  public function currentTempDirectory(): string {
    return \sys_get_temp_dir();
  }

  public async function beforeEachTestAsync(): Awaitable<void> {
    $file = \sprintf("%s/%s", $this->currentTempDirectory(), 'Test/Test1.hack');

    if (!\file_exists($file)) {
      return;
    }
    \unlink($file);
  }

  <<DataProvider('provideGenerater')>>
  public function test(ClassFileGenerator $generator): void {
    $file = \sprintf("%s/%s", $this->currentTempDirectory(), 'Test/Test1.hack');

    $result = $generator->generate(static::GENERATE_CLASS_NAME)->save();

    expect($result === CodegenFileResult::CREATE)->toBeTrue();
    expect(\file_exists($file))->toBeTrue();
  }
}

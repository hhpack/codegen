namespace HHPack\Codegen\Test;

use HHPack\Codegen\{ProjectFileGenerator, OutputNamespace};
use HHPack\Codegen\HackTest\{TestClassGenerator};
use Facebook\HackCodegen\{
  HackCodegenFactory,
  HackCodegenConfig,
  CodegenFileResult,
};
use HHPack\Codegen\Test\Mock\{NamedGeneratorMock};
use type Facebook\HackTest\{HackTest, DataProvider};
use function Facebook\FBExpect\expect;

final class ProjectFileGeneratorTest extends HackTest {
  const string GENERATE_CLASS_NAME = 'Test\\Test1';

  <<__Memoize>>
  public function currentTempDirectory(): string {
    return \sys_get_temp_dir();
  }

  public async function beforeEachTestAsync(): Awaitable<void> {
    $file = \sprintf("%s/%s", $this->currentTempDirectory(), 'Test/Test1.hh');

    if (!\file_exists($file)) {
      return;
    }
    \unlink($file);
  }

  public function provideGenerator(): vec<(ProjectFileGenerator)> {
    $namespace = new OutputNamespace('Foo\\Bar', $this->currentTempDirectory());
    $projectGenerator = ProjectFileGenerator::fromItems(
      [
        new NamedGeneratorMock(
          "test",
          "test",
          $namespace->map(TestClassGenerator::class),
        ),
      ],
    );
    return vec[tuple($projectGenerator)];
  }

  <<DataProvider('provideGenerator')>>
  public function test(ProjectFileGenerator $generator): void {
    $newTestClass = Pair {'test', static::GENERATE_CLASS_NAME};
    $result = $generator->generate($newTestClass)->save();

    $file = \sprintf("%s/%s", $this->currentTempDirectory(), 'Test/Test1.hh');
    expect($result === CodegenFileResult::CREATE)->toBeTrue();
    expect(\file_exists($file))->toBeTrue();
  }

}

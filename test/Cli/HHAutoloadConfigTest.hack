namespace HHPack\Codegen\Test;

use HHPack\Codegen\Cli\{HHAutoloadConfig};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class HHAutoloadConfigTest extends HackTest {
  public function testDevRoots(): void {
    $config = new HHAutoloadConfig(
      shape(
        'roots' => ['/example/path/to/'],
        'devRoots' => ['/example/path/to/'],
      ),
    );

    $v = $config->devRoots()->toImmVector();
    expect($v->at(0))->toBeSame("example/path/to");
  }
}

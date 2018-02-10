<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\Cli\{HHAutoloadConfig};
use HackPack\HackUnit\Contract\Assert;

final class HHAutoloadConfigTest {
  <<Test>>
  public function testDevRoots(Assert $assert): void {
    $config = new HHAutoloadConfig(shape(
      'roots' => ['/example/path/to/'],
      'devRoots' => ['/example/path/to/']
    ));

    $v = $config->devRoots()->toImmVector();
    $assert->string($v->at(0))->is("example/path/to");
  }
}

<?hh //strict

namespace HHPack\Codegen\Test;

use function HHPack\Codegen\Cli\{normalize_path};
use HackPack\HackUnit\Contract\Assert;

final class HHAutoloadTest {
  <<Test>>
  public function testNormalizePath(Assert $assert): void {
    $assert->string(normalize_path("/example/path/to"))->is("example/path/to");
    $assert->string(normalize_path("example/path/to/"))->is("example/path/to");
    $assert->string(normalize_path("/example/path/to/"))->is("example/path/to");
  }
}

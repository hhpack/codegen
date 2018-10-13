<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\{OutputNamespace};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class OutputNamespaceTest extends HackTest {
  public function testBelongsNamespace(): void {
    $ns = new OutputNamespace("Foo\\Bar", "/var/tmp");

    expect($ns->belongsNamespace("Bar1"))->toBeSame("Foo\\Bar\\Bar1");
    expect($ns->belongsNamespace("Bar1\\Bar2"))->toBeSame(
      "Foo\\Bar\\Bar1\\Bar2",
    );
  }
}

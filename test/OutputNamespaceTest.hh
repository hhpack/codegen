<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\{OutputNamespace};
use HackPack\HackUnit\Contract\Assert;

final class OutputNamespaceTest {
  <<Test>>
  public function belongsNamespace(Assert $assert): void {
    $ns = new OutputNamespace("Foo\\Bar", "/var/tmp");

    $assert->string($ns->belongsNamespace("Bar1"))->is("Foo\\Bar\\Bar1");
    $assert->string($ns->belongsNamespace("Bar1\\Bar2"))->is("Foo\\Bar\\Bar1\\Bar2");
  }
}

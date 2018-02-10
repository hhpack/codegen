<?hh //strict

namespace HHPack\Codegen\Test;

use HHPack\Codegen\{OutputClassName};
use HackPack\HackUnit\Contract\Assert;

final class OutputClassNameTest {
  <<Test>>
  public function fromWithNamespace(Assert $assert): void {
    $className = OutputClassName::fromString("Foo\\Bar");
    $assert->string($className->namespace())->is("Foo");
    $assert->string($className->name())->is("Bar");
  }

  <<Test>>
  public function fromWithoutNamespace(Assert $assert): void {
    $className = OutputClassName::fromString("Foo");
    $assert->string($className->namespace())->is("");
    $assert->string($className->name())->is("Foo");
  }
}

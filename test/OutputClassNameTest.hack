namespace HHPack\Codegen\Test;

use HHPack\Codegen\{OutputClassName};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class OutputClassNameTest extends HackTest {
  public function testFromWithNamespace(): void {
    $className = OutputClassName::fromString("Foo\\Bar");
    expect($className->namespace())->toBeSame("Foo");
    expect($className->name())->toBeSame("Bar");
  }

  public function testFromWithoutNamespace(): void {
    $className = OutputClassName::fromString("Foo");
    expect($className->namespace())->toBeSame("");
    expect($className->name())->toBeSame("Foo");
  }
}

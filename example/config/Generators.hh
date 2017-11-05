<?hh //strict

namespace HHPack\Codegen\Example;

use HHPack\Codegen\{OutputNamespace, GenerateType, ClassFileGenerator};
use HHPack\Codegen\Cli\{GeneratorProvider};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use HHPack\Codegen\Project\{PackageClassGenerator};
use function HHPack\Codegen\Cli\{namespace_of, map_to};

final class Generators implements GeneratorProvider {
  const LIB = 'HHPack\\Codegen\\Example';
  const LIB_TEST = 'HHPack\\Codegen\\Example\\Test';

  public function generators(
  ): Iterator<Pair<GenerateType, ClassFileGenerator>> {
    yield GenerateType::LibraryClass
      |> map_to($$, namespace_of(static::LIB, 'example/src')
        ->map(PackageClassGenerator::class));

    yield GenerateType::TestClass
      |> map_to($$, namespace_of(static::LIB_TEST, 'example/test')
        ->map(TestClassGenerator::class));
  }
}

<?hh //strict

namespace HHPack\Codegen\Example;

use HHPack\Codegen\{OutputNamespace, GenerateType, ClassFileGenerator};
use HHPack\Codegen\Cli\{CodegenGenerators};
use HHPack\Codegen\HackUnit\{TestClassGenerator};
use HHPack\Codegen\Project\{PackageClassGenerator};
use function HHPack\Codegen\Cli\{
  namespace_of,
  library,
  library_test
};

final class Generators implements CodegenGenerators {
  public function generators(
  ): Iterator<Pair<GenerateType, ClassFileGenerator>> {
    yield library(
      namespace_of('HHPack\Codegen\Example', 'example/src')
        ->map(PackageClassGenerator::class),
    );
    yield library_test(
      namespace_of('HHPack\Codegen\Example\\Test', 'example/test')
        ->map(TestClassGenerator::class),
    );
  }
}

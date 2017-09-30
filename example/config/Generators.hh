<?hh //strict

namespace HHPack\Codegen\Example;

use HHPack\Codegen\{ OutputNamespace, GenerateType, ClassFileGenerator };
use HHPack\Codegen\Cli\{ CodegenGenerators };
use HHPack\Codegen\HackUnit\{ TestClassGenerator };
use HHPack\Codegen\Project\{ PackageClassGenerator };

function generate_namespace_of(string $name, string $path) : OutputNamespace {
  return new OutputNamespace($name, $path);
}

function library(ClassFileGenerator $generator) : Pair<GenerateType, ClassFileGenerator> {
  return Pair { GenerateType::LibraryClass, $generator };
}

function library_test(ClassFileGenerator $generator) : Pair<GenerateType, ClassFileGenerator> {
  return Pair { GenerateType::TestClass, $generator };
}

final class Generators implements CodegenGenerators {
  public function generators(): Iterator<Pair<GenerateType, ClassFileGenerator>> {
    yield library(generate_namespace_of('HHPack\Codegen\Example', 'example/src')->map(PackageClassGenerator::class));
    yield library_test(generate_namespace_of('HHPack\Codegen\Example\\Test', 'example/test')->map(TestClassGenerator::class));
  }
}

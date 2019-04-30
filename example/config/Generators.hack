namespace HHPack\Codegen\Example;

use HHPack\Codegen\Contract\{NamedGenerator, GeneratorProvider};
use HHPack\Codegen\HackTest\{TestClassGenerator};
use HHPack\Codegen\Project\{PackageClassGenerator};
use function HHPack\Codegen\Cli\{define_generator, namespace_of};

final class Generators implements GeneratorProvider {
  const LIB = 'HHPack\\Codegen\\Example';
  const LIB_TEST = 'HHPack\\Codegen\\Example\\Test';

  public function generators(): Iterator<NamedGenerator> {
    yield define_generator("lib:class", "generate library class file.")
      ->mapTo(
        namespace_of(static::LIB, 'example/src')
          ->map(PackageClassGenerator::class),
      );

    yield define_generator("lib:testclass", "generate test class file.")
      ->mapTo(
        namespace_of(static::LIB_TEST, 'example/test')
          ->map(TestClassGenerator::class),
      );
  }
}

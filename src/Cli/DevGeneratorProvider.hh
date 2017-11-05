<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Cli;

use HHPack\Codegen\{GenerateType, FileGeneratable};
use Facebook\DefinitionFinder\{TreeParser, ScannedClass};

final class DevGeneratorProvider implements GeneratorProvider {

  public function __construct(private Traversable<string> $paths) {}

  public function generators(
  ): Iterator<Pair<GenerateType, FileGeneratable<string>>> {
    $generator = $this->loadFromPath($this->paths)->firstValue();

    if (is_null($generator)) {
      throw new \RuntimeException('generator not found');
    }

    $ref = new \ReflectionClass($generator);
    return $ref->newInstance()->generators();
  }

  private function loadFromPath(Traversable<string> $paths): ImmSet<string> {
    $generatorClassNames =
      ImmVector::fromItems($paths)
        ->map(($path) ==> $this->findGeneratorByPath($path));

    $result = Set {};

    foreach ($generatorClassNames as $generatorClassName) {
      $result = $result->concat($generatorClassName);
    }

    return $result->toImmSet();
  }

  private function findGeneratorByPath(string $path): ImmSet<string> {
    $parser = TreeParser::FromPath(getcwd().'/'.$path);
    return
      $parser->getClasses()
        ->filter(($class) ==> $this->isImplementProvider($class))
        ->map(($class) ==> $class->getName())
        ->toImmSet();
  }

  private function isImplementProvider(ScannedClass $class): bool {
    $implementInterface = ($interface) ==> $interface ===
    GeneratorProvider::class;
    $interfaces = $class->getInterfaceNames();
    $macthedInterfaces = $interfaces->filter($implementInterface);
    return $macthedInterfaces->count() > 0;
  }
}

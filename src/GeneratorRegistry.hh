<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen;

use HHPack\Codegen\Contract\{NamedGenerator};
use HH\Lib\{Vec};

final class GeneratorRegistry {
  private ImmMap<GeneratorName, PackageClassFileGeneratable> $registry;

  public function __construct(
    Traversable<Pair<GeneratorName, PackageClassFileGeneratable>> $generators,
  ) {
    $this->registry = ImmMap::fromItems($generators);
  }

  public function get(GeneratorName $name): PackageClassFileGeneratable {
    return $this->registry->at($name);
  }

  public static function fromItems(
    Traversable<NamedGenerator> $generators,
  ): this {
    $mappedGenerators = Vec\map(
      $generators,
      ($generator) ==> {
        return Pair {$generator->name(), $generator};
      },
    );
    return new self($mappedGenerators);
  }
}

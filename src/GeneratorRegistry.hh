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

final class GeneratorRegistry {
  private ImmMap<GenerateType, PackageClassFileGeneratable> $registry;

  public function __construct(
    Traversable<Pair<GenerateType, PackageClassFileGeneratable>> $generators,
  ) {
    $this->registry = ImmMap::fromItems($generators);
  }

  public function get(GenerateType $type): PackageClassFileGeneratable {
    return $this->registry->at($type);
  }
}

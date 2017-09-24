<?hh //strict

namespace HHPack\Codegen;

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

final class GeneratorRegistry {
  private ImmMap<GenerateType, ClassFileGenerator> $registry;

  public function __construct(
    Traversable<Pair<GenerateType,
    Pair<OutputNamespace, ClassFileGeneratable>>> $generators,
  ) {
    $items =
      ImmVector::fromItems($generators)->map(
        ($generator) ==> {
          list($type, $namespaceGenerator) = $generator;
          list($ns, $fgen) = $namespaceGenerator;
          return Pair {$type, new ClassFileGenerator($ns, $fgen)};
        },
      );
    $this->registry = ImmMap::fromItems($items);
  }

  public function get(GenerateType $type): ClassFileGenerator {
    return $this->registry->at($type);
  }
}

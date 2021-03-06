/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen;

use Facebook\HackCodegen\{CodegenFile};
use HHPack\Codegen\Contract\{FileGeneratable, NamedGenerator};

final class ProjectFileGenerator
  implements FileGeneratable<Pair<GeneratorName, ClassName>> {
  public function __construct(private GeneratorRegistry $registry) {}

  public function generate(
    Pair<GeneratorName, ClassName> $target,
  ): CodegenFile {
    list($alias, $name) = $target;
    $generator = $this->registry->get($alias);
    return $generator->generate($name);
  }

  public static function fromItems(
    Traversable<NamedGenerator> $generators,
  ): this {
    return new self(GeneratorRegistry::fromItems($generators));
  }
}

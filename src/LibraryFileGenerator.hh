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

use Facebook\HackCodegen\{CodegenFile};
use HHPack\Codegen\Contract\{FileGeneratable};

final class LibraryFileGenerator
  implements FileGeneratable<Pair<GenerateType, ClassName>> {
  public function __construct(private GeneratorRegistry $registry) {}

  public function generate(
    Pair<GenerateType, ClassName> $target,
  ): CodegenFile {
    list($type, $name) = $target;
    $generator = $this->registry->get($type);
    return $generator->generate($name);
  }

  public static function fromItems(
    Traversable<Pair<GenerateType, PackageClassFileGeneratable>> $generators,
  ): this {
    return new self(new GeneratorRegistry($generators));
  }
}

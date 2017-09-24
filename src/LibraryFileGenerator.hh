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

final class LibraryFileGenerator
  implements FileGeneratable<Pair<GenerateType, string>> {
  public function __construct(private GeneratorRegistry $registry) {}

  public function generate(
    Pair<GenerateType, string> $typeOfClass,
  ): CodegenFile {
    list($type, $name) = $typeOfClass;
    $generator = $this->registry->get($type);
    return $generator->generate($name);
  }

  public static function fromItems(
    Traversable<Pair<GenerateType, ClassFileGenerator>> $generators,
  ): this {
    return new self(new GeneratorRegistry($generators));
  }
}
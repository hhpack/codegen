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

use HHPack\Codegen\{ClassName, ClassFileGenerator};

final class GeneratorMapper {

  public function __construct(private DefinedMetaData $meta) {}

  public function mapTo(
    ClassFileGenerator $generator,
  ): DefinedGenerator {
    return new DefinedGenerator($this->meta, $generator);
  }
}

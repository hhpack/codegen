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

use HHPack\Codegen\{GenerateType, ClassFileGenerator};

interface GeneratorProvider {
  public function generators(
  ): Iterator<Pair<GenerateType, ClassFileGenerator>>;
}

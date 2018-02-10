<?hh //strict

/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen\Contract;

use HHPack\Codegen\{ClassName};

interface NamedGenerator extends FileGeneratable<ClassName> {
  public function name(): string;
  public function description(): string;
}

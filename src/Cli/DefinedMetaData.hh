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

use HHPack\Codegen\{GeneratorName};

final class DefinedMetaData {
  public function __construct(
    private GeneratorName $name,
    private string $description,
  ) {}

  public function name(): GeneratorName {
    return $this->name;
  }

  public function description(): string {
    return $this->description;
  }
}

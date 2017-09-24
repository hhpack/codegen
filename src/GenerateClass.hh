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

final class GenerateClass {
  public function __construct(
    private OutputClassName $className,
    private string $path,
  ) {}

  public function belongsNamespace(): string {
    return $this->className->namespace();
  }

  public function name(): string {
    return $this->className->name();
  }

  public function fileName(): string {
    return $this->path;
  }
}

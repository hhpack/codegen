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

/**
 * Generate class file
 */
final class GenerateClassFile {
  public function __construct(
    private OutputClassName $className,
    private string $path,
  ) {}

  /**
   * The namespace to which the class belongs
   */
  public function belongsNamespace(): string {
    return $this->className->namespace();
  }

  /**
   * Name of the class
   */
  public function name(): string {
    return $this->className->name();
  }

  /**
   * Path of class file
   */
  public function fileName(): string {
    return $this->path;
  }
}

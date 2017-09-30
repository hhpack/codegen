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

final class OutputClassName {

  public function __construct(
    private string $namespace,
    private string $name,
  ) {}

  public function namespace(): string {
    return $this->namespace;
  }

  public function name(): string {
    return $this->name;
  }

  public function withoutNamespace(string $namespace): string {
    $without = str_replace($namespace, '', $this->namespace);
    $c = explode('\\', $without);
    array_shift($c);
    $v = implode('\\', $c);

    if (strlen($v) <= 0) {
      return $this->name;
    }

    return $v.'\\'.$this->name;
  }

  public function relativeFilePath(string $namespace): string {
    $path = implode('/', explode('\\', $this->withoutNamespace($namespace)));
    return $path.'.hh';
  }

}

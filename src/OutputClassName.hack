/**
 * This file is part of hhpack\codegen.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Codegen;

use HH\Lib\{Str, Vec, C};

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
    $v = Str\replace($this->namespace, $namespace, '')
      |> Str\split($$, '\\')
      |> Vec\slice($$, 1)
      |> Str\join($$, '\\');

    if (Str\length($v) <= 0) {
      return $this->name;
    }

    return $v.'\\'.$this->name;
  }

  public function relativeFilePath(string $namespace): string {
    $path = Str\split($this->withoutNamespace($namespace), '\\')
      |> Str\join($$, '/');
    return $path.'.hack';
  }

  public static function fromString(string $name): this {
    $parts = Str\split($name, '\\');

    if (C\count($parts) <= 1) {
      $namespace = '';
    } else {
      $namespace = Vec\slice($parts, 0, C\count($parts) - 1)
        |> Str\join($$, '\\');
    }
    $className = C\lastx($parts);
    return new self($namespace, $className);
  }
}

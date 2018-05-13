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

use HHPack\Codegen\Contract\{ClassFileGeneratable};
use HH\Lib\{Str, Vec, C};
use Facebook\HackCodegen\{HackCodegenConfig, HackCodegenFactory};

final class OutputNamespace {

  public function __construct(
    private string $name,
    private string $mappedPath,
  ) {}

  public function name(): string {
    return $this->name;
  }

  public function path(): string {
    return $this->mappedPath;
  }

  /**
   * Return the new namespace to which it belongs
   *
   * ```hack
   * $output = new OutputNamespace("Foo\\Bar", ".");
   * echo $output->belongsNamespace("Foo1"); // Foo\\Bar\\Foo1
   * echo $output->belongsNamespace("Foo1\\Bar1"); // Foo\\Bar\\Foo1\\Bar1
   * ```
   */
  public function belongsNamespace(string $name): string {
    if (Str\length($name) <= 0) {
      return $this->name;
    }

    return $this->name.'\\'.$name;
  }

  public function relativeClassFilePath(OutputClassName $className): string {
    return $className->relativeFilePath($this->name);
  }

  /**
   * Return the class name belonging to the output target namespace
   *
   * ```hack
   * $output = new OutputNamespace("Foo\\Bar", ".");
   * $className = $output->classNameOf("Foo1");
   * echo $className->namespace() // Foo\\Bar
   * echo $className->name() // Foo1
   * ```
   */
  public function classNameOf(string $name): OutputClassName {
    $parts = Str\split($name, '\\');
    $className = C\lastx($parts);
    $subNamespace =
      $parts
        |> Vec\slice($$, 0, \count($$) - 1)
        |> Str\join($$, '\\');

    $namespace = $this->belongsNamespace($subNamespace);

    return new OutputClassName($namespace, $className);
  }

  public function resolveClassNameOf(
    OutputClassName $className,
  ): OutputClassName {
    $namespace = $this->belongsNamespace($className->namespace());
    return new OutputClassName($namespace, $className->name());
  }

  public function map<Tu as ClassFileGeneratable>(
    classname<Tu> $className,
  ): ClassFileGenerator {
    $config = (new HackCodegenConfig())->withRootDir($this->mappedPath);
    $factory = new HackCodegenFactory($config);
    return new ClassFileGenerator($this, $className::from($factory));
  }
}

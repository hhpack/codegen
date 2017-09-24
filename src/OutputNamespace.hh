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

  public function belongsNamespace(?string $name = null): string {
    if (is_null($name)) {
      return $this->name;
    }

    if (strlen($name) <= 0) {
      return $this->name;
    }

    return $this->name.'\\'.$name;
  }

  public function relativeClassFilePath(OutputClassName $className): string {
    return $className->relativeFilePath($this->name);
  }

  public function classNameOf(string $name): OutputClassName {
    $names = explode('\\', $name);
    $className = array_pop($names);
    $subNamespace = implode('\\', $names);

    $namespace = $this->belongsNamespace($subNamespace);

    return new OutputClassName($namespace, $className);
  }

  public function map<Tu as ClassFileGeneratable>(
    classname<Tu> $className,
  ): ClassFileGenerator {
    $config = new HackCodegenConfig($this->mappedPath);
    $factory = new HackCodegenFactory($config);
    return new ClassFileGenerator($this, $className::from($factory));
  }

  <<__Deprecated('Please use map method instead')>>
  public function createGenerator<Tu as ClassFileGeneratable>(
    classname<Tu> $className,
  ): ClassFileGenerator {
    $config = new HackCodegenConfig($this->mappedPath);
    $factory = new HackCodegenFactory($config);
    return new ClassFileGenerator($this, $className::from($factory));
  }

}
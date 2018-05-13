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

use HH\Lib\{Str};
use function \Facebook\TypeAssert\{matches_type_structure};

final class HHAutoloadConfig {
  const type T = shape(
    'roots' => Traversable<string>,
    'devRoots' => Traversable<string>,
  );

  public function __construct(private this::T $config) {}

  public function devRoots(): ImmSet<string> {
    return
      ImmSet::fromItems($this->config['devRoots'])
        ->map(($path) ==> $this->normalizePath($path));
  }

  /**
   * Load the configuration of hh_autoload
   */
  public static function fromFile(string $jsonPath): this {
    if (!\file_exists($jsonPath)) {
      throw new \RuntimeException(\sprintf("File %s not found", $jsonPath));
    }

    $autoloadJson = \file_get_contents($jsonPath);
    $json = \json_decode($autoloadJson, true, 512, \JSON_FB_HACK_ARRAYS);
    $validJson =
      matches_type_structure(type_structure(self::class, 'T'), $json);

    if (!Shapes::keyExists($validJson, 'devRoots')) {
      throw new \RuntimeException('devRoots is not in the configuration');
    }

    return new self($validJson);
  }

  public static function fromWorkingDirectory(): this {
    return static::fromFile(\getcwd().'/hh_autoload.json');
  }

  /**
   * Return the normalize path
   */
  private function normalizePath(string $path): string {
    $normalizePath = $path;

    // /path/to -> path/to
    if (Str\slice($normalizePath, 0, 1) === '/') {
      $len = Str\length($normalizePath);
      $normalizePath = Str\slice($normalizePath, 1, $len);
    }

    $lastIndex = Str\length($normalizePath) - 1;

    if (Str\slice($normalizePath, $lastIndex, 1) === '/') {
      $normalizePath = Str\slice($normalizePath, 0, $lastIndex);
    }

    return $normalizePath;
  }
}

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

type HHAutoloadConfig = shape(
  'roots' => Traversable<string>,
  'devRoots' => Traversable<string>,
);

/**
 * Return the directory with the source for development
 */
function dev_roots(): ImmSet<string> {
  $config = load_autoload_config();
  $normalizer = fun('\HHPack\Codegen\Cli\normalize_path');
  return ImmSet::fromItems($config['devRoots'])->map($normalizer);
}

/**
 * Return the normalize path
 */
function normalize_path(string $path): string {
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

/**
 * Load the configuration of hh_autoload
 */
function load_autoload_config(): HHAutoloadConfig {
  $jsonPath = getcwd().'/hh_autoload.json';

  if (!file_exists($jsonPath)) {
    throw new \RuntimeException(sprintf("File %s not found", $jsonPath));
  }

  $autoloadJson = file_get_contents($jsonPath);
  $json = json_decode($autoloadJson, true);

  if (!array_key_exists('devRoots', $json)) {
    throw new \RuntimeException('devRoots is not in the configuration');
  }

  return shape('roots' => $json['roots'], 'devRoots' => $json['devRoots']);
}
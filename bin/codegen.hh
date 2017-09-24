<?hh //partial

namespace HHPack\Codegen;

use Facebook\HackCodegen\{
  HackCodegenConfig,
  HackCodegenFactory,
  HackBuilderValues,
  CodegenFileResult,
  HackBuilderKeys,
  CodegenFile,
  CodegenClass,
  CodegenMethod
};
use HHPack\Codegen\HackUnit\TestClassGenerator;
use HHPack\Codegen\HHGenerator;
use HHPack\Codegen\OutputNamespace;

$autoloadFiles = [
  __DIR__.'/../vendor/hh_autoload.php',
  __DIR__.'/../../../hh_autoload.php',
  __DIR__.'/../vendor/autoload.php',
  __DIR__.'/../../../autoload.php',
];
$composerInstall = false;
foreach ($autoloadFiles as $autoloadFile) {
  if (!file_exists($autoloadFile)) {
    continue;
  }
  require $autoloadFile;
  $composerInstall = true;
  break;
}
if (!$composerInstall) {
  echo
    'You must set up the dependencies, run the following commands:'.
    PHP_EOL.
    'curl -s http://getcomposer.org/installer | php'.
    PHP_EOL.
    'php composer.phar install'.
    PHP_EOL
  ;
  exit(1);
}

unset($composerInstall, $autoloadFiles, $autoloadFile);

function main(): void {
  $a = new HHGenerator(
    new Configuration(
      new OutputNamespace('HHPack\Codegen', getcwd().'/src'),
    ),
  );
  $a->generateTestFile('A')->save();
}
main();
<?php

function import_get_files($type) {
  $files = array();
  $handle = @fopen("index.imports.cfg", "r");
  if ($handle) {
    $in_section = FALSE;
    while (($line = fgets($handle)) !== false) {
      $trimmed = trim($line);
      if (strlen($trimmed) > 0) {
        if (strncmp($line, ' ', 1)) {
          if ($trimmed === $type) {
            $in_section = TRUE;
          } else if ($in_section) {
            break;
          }
        } else if ($in_section) {
            $files[] = $trimmed;
        }
      }
    }
    fclose($handle);
  }
  return $files;
}

function import_templates() {
  $templates = import_get_files('templates');

  foreach ($templates as $template) {
    $content = file_get_contents('templates/' . $template . '.html.template');
    if ($content) {
      print '<script type="text/x-handlebars" data-template-name="' . $template . '">'
              . $content
              . '</script>';
    }
  }
}

function import_javascript() {
  $scripts = import_get_files('javascript');
  foreach ($scripts as $script) {
    print '<script src="js/' . $script . '.js"></script>';
  }
}

function import_css() {
  $files = import_get_files('css');
  foreach ($files as $file) {
    print '<link href="css/' . $file . '.css" rel="stylesheet" media="screen">';
  }
}

<?php

function import_templates($templates) {
  foreach ($templates as $template) {
    $content = file_get_contents('templates/' . $template . '.html.template');
    if ($content) {
      print '<script type="text/x-handlebars" data-template-name="' . $template . '">'
              . $content
              . '</script>';
    }
  }
}

function import_javascript($scripts) {
  foreach ($scripts as $script) {
    print '<script src="js/' . $script . '.js"></script>';
  }
}

function import_css($files) {
  foreach ($files as $file) {
    print '<link href="css/' . $file . '.css" rel="stylesheet" media="screen">';
  }
}


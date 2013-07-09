<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Trajectories</title>

    <?php
    include_once 'imports.php';

    import_css(array(
        'normalize',
    ));
    ?>
  </head>
  <body>
    <script type="text/x-handlebars" data-template-name="application">
      <h1>Trajectories</h1>
    </script>

    <?php
    import_templates(array(
        'application',
        'index',
        'simulations',
    ));

    import_javascript(array(
        'libs/jquery-1.9.1',
        'libs/handlebars-1.0.0-rc.4',
        'libs/ember-1.0.0-rc.6',
        'libs/ember-data-0.13',
    ));

    import_javascript(array(
        'app',
        'router',
    ));
    ?>
  </body>
</html>

<?php
/**
 * Using 'myapi' module
 * this page is entirely output using the 'myapi module'
 */
?>

<?php
if ($messages):
  print $messages;
endif;


/**
 * Node Info
 */
//dpm($node_info);

/**
 * Login Form
 */
if (!$variables['logged_in']) {
  $elements = drupal_get_form("user_login");
  $form = drupal_render($elements);
  echo $form;
}

?>

<?php
  $base_url = $GLOBALS['base_url'];
  $current_path = '/' . current_path();
  $url = $base_url . $current_path;
  $context = stream_context_create(array('http' => array('header'=>'Connection: close\r\n')));

  /**
   * Helper Functions
   * @param $id
   * the id for the script tag
   * @param $name
   * the name of the file without the extension or path
   * @param $partial
   * is this a partial file
   */
  function handlebars ($id, $filename, $partial=FALSE) {
    $current_theme = variable_get('theme_default','none');
    $theme_path = path_to_theme($current_theme);
    print "<script id='{$id}' type='text/x-handlebars-template'>";
    if (!$partial) {
      include("{$theme_path}/handlebars/" . $filename . '.hb.php');
    } else {
      include("{$theme_path}/handlebars/partials/" . $filename . '.hb.php');
    }
    print "</script>";
  }

  /**
   * Add templates to build page
   */
  handlebars('list-item-partial', 'list-item', TRUE);
  handlebars('main-menu', 'menu');
  handlebars('site-header', 'header');
  handlebars('body', 'body');
?>

<script>
  //bootstrap the data so no initial call is required
	var bootstrap = {
		siteNav: <?php echo file_get_contents("{$base_url}/api/menu/main-menu",false,$context) ;?>,
    node: <?php echo file_get_contents("{$base_url}/api/node/{$node_info['nid']}",false,$context) ;?>
	}
</script>


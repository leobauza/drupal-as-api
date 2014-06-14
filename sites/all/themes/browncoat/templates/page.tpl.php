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

//dpm($page);
/**
 * Node Info
 */
//dpm($node_info);

/**
 * Associations (views)
 */
if (isset($node->myapi_test)) {
  $assoc_views_field = field_view_field('node', $node, 'myapi_test');
  $assoc_views = array();
  if (isset($assoc_views_field['#items'])) {
    foreach($assoc_views_field['#items'] as $key) {
      $assoc_views[] = $key['value'];
    }
  }

  $assoc_views = "?views=" . implode('+', $assoc_views);

  // if (isset($assoc_views_field['#items'][0]['value'])) {
  //   $myapi_default = $assoc_views_field['#items'][0]['value'];
  // }
}
//dpm($node->myapi_test);


/**
 * Get Related Views
 * I am doing this with set variable right now...this isn't a good idea
 * need to create schema to save directly to the node like $node->views
 * which would be accessed like.... $node_info['views']
 */
//$mnd = $myapi_node_data
// $mnd = variable_get('myapi_node_data', '');
// $node_views = isset($mnd['node_views'][$node_info['nid']])? $mnd['node_views'][$node_info['nid']] : '';
// dpm($node_views);

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

  /**
   * create a url with a number of parameters formed
   * info about the page. this way there is one file_get_contents
   * for all the data needed to form the page:
   * {$base_url}/api/page/{$node_info['nid']}?menu=main-menu&blocks=1,2,3
   *
   * Also: set defaults on a per content type basis...
   * ^ should that happen on tempaltes here on on the myapi side?
   */

	var bootstrap = <?php echo file_get_contents("{$base_url}/api/page/{$node_info['nid']}{$assoc_views}",false,$context) ;?>

	// siteNav: <?php echo file_get_contents("{$base_url}/api/menu/main-menu",false,$context) ;?>,
  // node: <?php echo file_get_contents("{$base_url}/api/node/{$node_info['nid']}",false,$context) ;?>

</script>



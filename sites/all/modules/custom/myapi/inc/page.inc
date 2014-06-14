<?php
/**
 * Returns a bootstrap object
 *
 * @Resource URL
 * /api/page/ [sample: /api/page/1]
 *
 * @param $id
 * ID for the page
 */
function getPage($id) {
  // $type = node_type_load('page');
  // print json_encode($type);
  $g = $_GET;
  // foreach ($g as $k => $v) {
  //   print("{$k} is {$v} -- AND -- ");
  // }
  //print_r($g);

  $node = getNode($id);
  $menu = getMenu('main-menu');

  $output = array(
    'querie' => $g['q'],
    'node' => $node,
    'menu' => $menu
  );

  if (isset($_GET['views'])) {
    $view_name = $_GET['views'];
    $output['views'] = getView($view_name);
  }

  return $output;
}

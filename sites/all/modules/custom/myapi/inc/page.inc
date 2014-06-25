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

  //I don't need get parameters at all because I have all the
  //node information!!
  //return $node->language;
  //return $node->assoc_views;
  //return $node->assoc_blocks;

  $output = array(
    'querie' => $g['q'],
    'node' => $node,
    'menu' => $menu
  );

  if (isset($_GET['views'])) {
    $view_names = $_GET['views'];
    $output['views'] = getViews($view_names);
  }

  return $output;
}

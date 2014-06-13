<?php
/**
 * Returns a view object
 *
 * @Resource URL
 * /api/view/ [sample: /api/view/articles]
 *
 * @param $name
 * name of the view
 * @param $page
 * page number for the view if paginated
 */
function getView($name, $page=0) {

  $view = views_get_view($name);

  $view->init_display();
  $view->current_page = $page;

  $view->pre_execute();
  $view->execute();
  $view_result = $view->result;

  $rows = array();
  foreach ($view_result as $row) {
    $rows[$row->nid] = $row;
  }

  return $rows;

}

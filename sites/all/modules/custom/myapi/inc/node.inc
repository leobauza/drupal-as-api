<?php
/**
 * Returns a json object of fields
 *
 * @Resource URL
 * /api/node/ [sample: /api/node/1]
 *
 * @param $id
 * The node id
 */
function getNode($id) {

  $fields = node_load($id);

  $fields->custom_fields = array();
  foreach ($fields as $field => $value) {
    if (strpos($field, 'field_') !== FALSE && !empty($value)) {
      $fields->custom_fields[$field] = $value;
    }
  }

  if (empty($fields->custom_fields)) {
    unset($fields->custom_fields);
  }


  echo json_encode($fields);

}


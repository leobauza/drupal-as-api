<?php
/**
 * Returns a json object of fields
 *
 * @Resource URL
 * /api/node/ [sample: /api/node/1]
 *
 * @param $id
 * The node id
 * @param $internal
 * internal calls are calls from within myapi aka not a http request
 */
function getNode($id, $internal=FALSE) {

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

  if ($internal === TRUE) {
    return $fields;
  } else {
    echo json_encode($fields);
  }


}


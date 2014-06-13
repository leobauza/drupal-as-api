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
      $fields->custom_fields[$field] = field_view_field('node', $fields, $field)['#items'][0];
      //unset the old values
      unset($fields->$field);
    }
    if ($field === 'body') {
      $fields->body = field_view_field('node', $fields, 'body')['#items'][0];
    }
  }

  if (empty($fields->custom_fields)) {
    //no custom fields so unset the propety
    unset($fields->custom_fields);
  }


  //get rid of some properties you dont need
  unset($fields->rdf_mapping);

  return $fields;

}


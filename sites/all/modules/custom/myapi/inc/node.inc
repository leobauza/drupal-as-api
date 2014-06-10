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

  /**
   * !! NEED TO CHANGE CODE SO THAT I AM NOT USING 'UND'
   * !! AS IN body['und']['value']
   */

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


  if ($internal === TRUE) {
    return $fields;
  } else {
    echo json_encode($fields);
  }


}


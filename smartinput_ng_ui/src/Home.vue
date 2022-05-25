<script setup lang="ts">
import { computed, Ref, ref } from "vue";
import { http } from "@tauri-apps/api";
import colorPicker from "@caohenghu/vue-colorpicker";

const client = await http.getClient();
let effects = ref({});

interface EffectOptions {
  [id: string]: string | number | boolean;
}

let effectOptionsData: Ref<Record<string, string | number | boolean>> = ref({});

const activeEffectName = computed(() => {
  let found = null;
  for (const key in effects.value) {
    console.log("key", key);
    const value = effects.value[key];
    if (value.active) {
      found = key;
      break;
    }
  }
  return found;
});

const activeEffectSettings = computed(() =>
  activeEffectName.value ? effects.value[activeEffectName.value] : null
);

function patchEffectOptionsData(effectName: string) {
  let availableOptions = effects.value[effectName].options;

  for (const optionName in availableOptions) {
    if (effectOptionsData.value[optionName] === undefined) {
      effectOptionsData.value[optionName] =
        availableOptions[optionName].default;
      console.log("x", effectOptionsData.value);
    }
  }
}

async function getEffects() {
  return await (
    await client.get("http://127.0.0.1:12853/effects")
  ).data;
}

async function changeEffect(effectName: string) {
  console.log("yx", effectOptionsData.value);
  patchEffectOptionsData(effectName);
  console.log("x", effectOptionsData.value);
  await client.post(`http://127.0.0.1:12853/set_effect/${effectName}`, {
    type: "Json",
    payload: effectOptionsData.value,
  });
  effects.value = await getEffects();
}

// function convertColor(color) {
//   const { r, g, b, a } = color.hex;
//   return [r, g, b];
// }

effects.value = await getEffects();
</script>

<template>
  <div class="bg-bg-1 h-screen w-screen flex flex-row p-8 gap-8">
    <section class="w-1/3">
      <h2 class="font-bold text-white text-3xl pb-4">Effects</h2>
      <div class="grid lg:grid-rows-2 lg:grid-flow-col gap-4">
        <button
          v-for="(effect, effect_name) in effects"
          :key="effect_name"
          class="
            text-white
            p-6
            rounded-xl
            text-xl
            hover:scale-95
            transition-all
          "
          :class="{
            'bg-green-800': effect.active,
            'bg-bg-2': !effect.active,
          }"
          @click="changeEffect(effect_name)"
        >
          {{ effect.friendlyName }}
        </button>
      </div>
    </section>
    <section class="bg-bg-2 flex-grow rounded-xl p-8 text-white">
      <h2 class="font-bold text-white text-3xl">
        <p v-if="activeEffectName">
          Settings for {{ effects[activeEffectName].friendlyName }}
        </p>
        <p v-else>Settings</p>
      </h2>
      <table v-if="activeEffectName">
        <tr
          v-for="(option, option_name) in activeEffectSettings.options"
          :key="option_name"
        >
          <td class="pr-4">
            <h3 class="font-bold">{{ option.friendly_name }}</h3>
          </td>
          <td v-if="option.type === 'int'" class="flex gap-2">
            <p>{{ option.min }}</p>
            <input
              v-model.number="effectOptionsData[option_name]"
              type="range"
              :min="option.min"
              :max="option.max"
            />
            <p>{{ option.max }}</p>
          </td>
          <td v-else-if="option.type === 'color'">
            <color-picker
              class="!w-64"
              theme="dark"
              :color="effectOptionsData[option_name]"
              @changeColor="
                (color) => {
                  effectOptionsData[option_name] = color.hex;
                }
              "
            />
          </td>
        </tr>
      </table>
    </section>
  </div>
</template>


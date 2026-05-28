"use client";

import { useMemo, useRef, useState } from "react";

import { Movie } from "@/graphql/generated/graphql";

import { computeLayout } from "./compute-layout";
import { useGridCols } from "./use-grid-cols";

import { MediaGridElement } from "./grid-elem/media-grid-element";

type Props = {
    medias: Movie[];
};

export default function MediaGrid({
    medias,
}: Props) {

    const [expandedId, setExpandedId] =
        useState<string | null>(null);

    const [transitioningIds, setTransitioningIds] =
        useState<Set<string>>(new Set());

    const [isAnimatingLayout, setIsAnimatingLayout] =
        useState(false);

    const [shouldScroll, setShouldScroll] = 
        useState(false);

    const scrollTarget = useRef<HTMLElement>(null);

    const gridCols = useGridCols();

    const layouts = useMemo(() => {

        return computeLayout(
            medias,
            expandedId,
            gridCols
        );

    }, [medias, expandedId, gridCols]);

    function handleClick(target: HTMLElement, mediaId: string) {

        if (isAnimatingLayout) {
            return;
        }

        const ids = new Set<string>();

        ids.add(mediaId);

        if (expandedId && expandedId !== mediaId) {
            ids.add(expandedId);
        }

        scrollTarget.current = target;
        setShouldScroll(true);
        
        setTransitioningIds(ids);

        setTimeout(() => {

            setIsAnimatingLayout(true);
            
            setExpandedId(prev =>
                prev === mediaId
                    ? null
                    : mediaId
            );

        }, 120);
    }

    return (

        <div
            className="
                grid
                auto-rows-[120px]
                gap-4
            "
            style={{
                gridTemplateColumns:
                    `repeat(${gridCols}, minmax(0, 1fr))`
            }}
        >

            {medias.map((media) => {

                const layout =
                    layouts.find(
                        l => l.id === media.id
                    );

                if (!layout) {
                    return null;
                }

                const expanded = expandedId === media.id;

                const isTransitioning = transitioningIds.has(media.id);

                const animateSize = isTransitioning || expanded;

                return (
                    <MediaGridElement
                        key={media.id}
                        media={media}
                        layout={layout}
                        expanded={expanded}
                        isTransitioning={isTransitioning}
                        isAnimatingLayout={isAnimatingLayout}
                        shouldAnimateSize={animateSize}
                        scrollTarget={scrollTarget}
                        setTransitioningIds={setTransitioningIds}
                        setIsAnimatingLayout={setIsAnimatingLayout}
                        handleClick={handleClick}
                    />
                );
            })}

        </div>
    );
}